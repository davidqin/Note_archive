awebook部署中遇到的问题
---

记录部署过程中遇到的一些比较耗时的问题。

### capistrano deploy名字空间 中的 upload 问题

执行

    upload('bin/rvm_install.sh','~/rvm_install.sh')

遇到

    wrong number of arguments (2 for 0) (ArgumentError)

经过search发现，upload在deploy名字空间下是一个task。

```
12:55 <MojoLA> I think I've discovered what's going on ... 
12:56 <MojoLA> when I call "upload" within the :deploy namespace, it's trying to call a task named deploy:upload 
12:57 <MojoLA> now I just have to figure out a way around it 
13:07 <MojoLA> yep, if you're inside the :deploy namespace "upload" is masked by a task of the same name 
13:08 <MojoLA> so if I call out to a different namespace, I can do my uploads from there 
```

##### 解决的办法
	
	＃ 调用top下的upload
    top.upload('bin/rvm_install.sh','~/rvm_install.sh')

### capistrano 本地用户名字与服务器不同

capistrano默认使用当前系统当前用户名称作为脚本中的user，来登陆远程服务器。而我的本地的user是davidqhr而远程的是david，二者不一致，会出问题。有一种解决方案是在我每次执行task的时候，我手动输入用户名来指定我需要用哪一个用户登陆远程服务器，但是我并不想这个做，感觉很麻烦。

##### 解决办法

写一个yml配置，根据配置是否存在，来决定是否修改登陆user。

##### Capfile

```
if File.exist?(File.join(Dir.pwd, "..", "config.yml"))
  require 'yaml'
  user_config = YAML.load_file(File.join(Dir.pwd, "..", "config.yml"))
  set :user, user_config["server_user_name"]
end% 
```

##### yml

    server_user_name: david
 
### solr index没有放到share中

由于solr中的索引没有放到shared文件夹中，导致每次更新代码的时候，以前的搜索索引都会被清除。

##### 解决办法

```
desc "start solr"
task :start, :roles => :app do
  run "cd #{current_path} && RAILS_ENV=production bundle exec sunspot-solr start --port=8983 --data-directory=#{shared_path}/solr/data --pid-dir=#{shared_path}/pids --log-file=#{shared_path}/solr/log --solr-home=#{current_path}/solr"
end

  # 其他task同理
  ...
  ...
```

### solr 进程杀的不干净

在ubuntu下，通过```rake sunspot:solr:stop RAILS_ENV=production```关闭solr的时候，会有一个进程无法终止，反复开关solr几次后，会留下很多无用的进程。但是在MacOS中没有发现这个问题。

##### 解决办法

```
desc "stop solr"
task :stop, :roles => :app do
  run "cd #{current_path} && RAILS_ENV=production bundle exec sunspot-solr stop ..."
  run "ps aux | grep solr | awk '{ print $2 }' | head -n 1 | xargs sudo kill -9"
end
```

### 多用户的rvm

一个需要注意的地方

```
NOTE: To Multi-User installers, please do NOT forget to add your users to the 'rvm'.
      The installer no longer auto-adds root or users to the rvm group. Admins must do this.
      Also, please note that group memberships are ONLY evaluated at login time.
      This means that users must log out then back in before group membership takes effect!
```

### passenger 在 global app在其他gemset

### 非交互环境中修改root密码 脚本中修改root密码

```
def set_password(message)
  raise "need a block" unless block_given?

  password = Capistrano::CLI.password_prompt(message)
  confirmation = Capistrano::CLI.password_prompt("confirmation: ")
  if confirmation == password
    yield password
  else
    abort("password and confirmation doesn't match!")
  end
end

set_password "Set root password: " do |root_password|
  run "printf '#{root_password}\\n#{root_password}\\n' |sudo passwd root"
end
```
    
优点在于非交互，适合用在脚本中。缺点在于密码会被显示在标准输出。

 
### sudoers的权限只能是440

可以使用sudo命令

### echo与>或者>>配合使用权限问题

经常会有将某些文本加入到某个文件中的需求，例如：

    $ echo "rvm use 1.9.3@gemset" > ./.vimrc
    $ echo "export some_string" >> ~/.bashrc
    
但是想要修改或创建的的文件权限不足的时候就会有问题，以下这种方式是**无效**的

    $ sudo echo "rvm use 1.9.3@gemset" > ./.vimrc
    $ sudo echo "export some_string" >> ~/.bashrc
    
    ＃结果
    -bash: xxx.xxx: Permission denied

无效的原因在于，sudo只作用于echo，而后面的**>**与**>>**仍是以当前用户权限执行。

##### 解决的办法
	
	# 通过sh -c，使sudo提升的权限扩展到这个命令范围
    $ sudo sh -c 'echo "some_sring" >> ~/.bashrc'
    
    # 使用tee
    $ echo "some_string" | sudo tee -a ~/.bashrc

### 指定用户执行脚本，用户没有登陆全县

需求背景：需要使用一个无shell权限的用户，来执行定期任务。

    sudo su -s /bin/bash -l -c "rvm use 1.9.3-p0@backup && backup perform -t awebook" blh
    
### backup

### passenger重启影响另外一个程序
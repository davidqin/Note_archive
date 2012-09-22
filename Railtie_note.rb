Rails::Railtie

查看源码时候发现了一个工具类：
require 'active_support/concern' tools class
ActiveSupport::Concern
做的事情很简单，看看代码就能明白

值得注意的是Rails::Railtie的new方法是private的

railtie模块中autoload了如下两个模块
autoload :Configurable,  "rails/railtie/configurable"
autoload :Configuration, "rails/railtie/configuration"
第一个模块的作用是为railstie的子类添加一些方法
例如子类不能被继承（几个特例除外 Rails::Railtie Rails::Engine Rails::Application）
单个实例

第二个模块在我理解就是一个容器，里边存储了配置信息
要注意的是，Configuration中的变量多为类变量

经常在application.rb看到如下例子
config.assets.enabled = true
其中config是一个方法
视频中指出的config方法，当时我有个疑问，就是config方法是实例方法
但是我们在使用的时候却当成类方法使用
查找了一下config
是在railtie/configurable.rb中定义的
delegate :config, :to => :instance
config的实质就是一个railtie的子类实例的config方法（单例模式）
这样的好处就是在initializers文件夹中，你可以这样调用
Rails.application.config....

接下来railtie没什么了

进入engine
继承自railtie

先看 Engine::Configuration
同样 Engine::Configuration < ::Rails::Railtie::Configuration
这里有了一个本质的变化
engine中有了middleware这一个函数
返回的结果是一个Rails::Configuration::MiddlewareStackProxy的例子
这里用的是一个代理类，视频中也特殊强调了这个地方，因为，middleware的包裹并不是这个时候完成的
这里只是一个简单的存储
形成一个middleware stack
generateors函数是同样道理的
paths中看到了一个rails app的基本骨架

回到engine，发现有一个call方法，这个是rack app的入口
调用了app的call方法

app中的 config.middleware = config.middleware.merge_into(default_middleware_stack)
干的事情就是将engine自己的middleware包裹在default_middleware_stack外边，并返回包装后的数组
engine自己的middleware代码中我并没有找到，应该事在使用的过程中使用者自己添加的

接下来的
config.middleware.build(endpoint)
是最重要的地方

endpoint是可以通过api修改的
不做任何修改的时候默认事routes
routes是一个 ActionDispatch::Routing::RouteSet.new     -----一会细看
endpoint的含义应该是middleware stack的build最后到哪结束 

build是 ActionDispatch::MiddlewareStack 的函数
一次调用每一个middleware的build函数，生成一个个新的app包裹以前的app

最后生成的app 是一个 ActionDispatch::Static 实例
app中有一个实例变量@app
其中存储着最外层的middleware实例
这个middleware中依然存在一个@app，其中存储着下一层的middleware的实例，递归下去
当然到最后，会发现#<ActionDispatch::Routing::RouteSet:0xaaf94ac>


再继续看application
Application < Engine
多了一些middleware而已

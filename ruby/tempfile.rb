require 'tempfile'  
  
tmp = Tempfile.new("tmp")  
  
tmp.path # => /tmp/tmp20110928-12389-8yyc6w 不唯一  
  
tmp.write("This is a tempfile")  
tmp.rewind  
tmp.read # => "This is a tempfile"  
  
tmp.close  
tmp.unlink # => 删除文件 

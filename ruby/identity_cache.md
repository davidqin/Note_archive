
identity_cache
=======

一些基础
----
### ruby
allocate创建类实例分配空间的过程
### class variable(@@x) 与 class instance variable(@x)

```
# class variable
# 整个继承体系公用@xx
class A
  @@x = 100
end

class B < A
end

```
```
# class instance variable
# 继承体系中的每一个类独享
class A
  @x = 1
end

class B < A
end
```
ActiveSupport有实现：activesupport-3.2.14/lib/active_support/core_ext/class/attribute.rb

参考资料：http://ihower.tw/blog/archives/4878
### ActiveRecord 相关
```
User.quoted_primary_key 
 => "`id`"
User.quoted_table_name
 => "`users`"

# coder的概念
class Post < ActiveRecord::Base
end
coder = {}
Post.new.encode_with(coder)
coder # => { 'id' => nil, ... }

class Post < ActiveRecord::Base
end

post = Post.allocate
post.init_with('attributes' => { 'title' => 'hello world' })
post.title # => 'hello world'
```
identity_cache部分
--------
### fetch_by_id
根据id生成cache_key，在缓存中查找cache_key，如果没有的话获取对象，拿到对象coder，存入缓存，也就是说，缓存对象实际上缓存的是对象的coder。
通过coder拿到object，返回object
### fetch
fetch_by_id的找不到抛异常版本
### ActiveRecord::Base.fetch_multi
之所以这样命名本段，是为了区别IndentityCache.fetch_multi
find_batch
### cache_index

生成一些实例方法
例如

```
class Product
  include IdentityCache
  cache_index :name, :vendor
end

Product.fetch_by_name_and_vendor

```
#### 可选的参数 options[:unique]

最直接的解释就是在sql中是否加入'LIMIT 1'，换言之，返回id还是ids

true的时候生成两个方法

`fetch_by_name_and_vendor`
`fetch_by_name_and_vendor!` 返回结果空得时候抛出异常

空得时候只会有不抛异常的方法。

### cache_has_many

```

class Product
  cached_has_many :orders
end

singular_association = association.to_s.singularize 
#=> order

options[:association_class]       ||= reflect_on_association(association).klass
#=> Order

options[:cached_accessor_name]    ||= "fetch_#{association}"
#=> fetch_orders

options[:ids_name]                ||= "#{singular_association}_ids"
#=> order_ids

options[:cached_ids_name]         ||= "fetch_#{options[:ids_name]}"
#=> fetch_order_ids

options[:ids_variable_name]       ||= "cached_#{options[:ids_name]}"
#=> cached_order_ids

options[:records_variable_name]   ||= "cached_#{association}"
#=> cached_orders

options[:population_method_name]  ||= "populate_#{association}_cache"
#=> populate_orders_cache

options[:prepopulate_method_name] ||= "prepopulate_fetched_#{association}"
#=> prepopulate_fetched_orders
```
相当于向order model中注入以下方法

```
class Order
  attr_reader :cached_order_ids

  def fetch_order_ids
    populate_orders_cache unless @cached_order_ids
    @cached_order_ids
  end

  def populate_orders_cache
    @cached_order_ids = order_ids
    association_cache.delete(:orders)
  end

  def fetch_orders
    if IdentityCache.should_cache? || orders.loaded?
      populate_orders_cache unless @cached_order_ids || @cached_orders
      @cached_orders ||= Order.fetch_multi(*@cached_order_ids)
    else
      orders
    end
  end

  def prepopulate_fetched_orders(records)
    @cached_orders = records
  end
end
```
Order.fetch_multi 注意区别 IndentityCache.fetch_multi


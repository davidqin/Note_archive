
identity_cache源码阅读笔记
=======
一些基础
----
### ruby
allocate创建类实例分配空间的过程
### Class variable(@@x) 与 Class instance variable(@x)

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
```
class User < ActiveRecord::Base
  serialize :preferences
end

user = User.create(preferences: { "background" => "black", "display" => large })
User.find(user.id).preferences # => { "background" => "black", "display" => large }

User.serialized_attributes
# => {"preferences"=>#<ActiveRecord::Coders::YAMLColumn:0x007fa079afc5a0 @object_class=Object>}
```

identity_cache部分
--------
## 概述
模块分割很清晰：

- 顶级空间下的工具函数
- cache_key_generator
- query_api
- cache_proxy
- dsl


## query_api部分

### coder_from_record
##### 功能
将一个record整理成一个hash，hash包含很多属性（下面详细解释），缓存这个对象的时候，实际上缓存的是这个hash
##### 结构
coder的结构是

```
{
  class: Order,
  attributes: {
  	id: 1,
  	...
  },
  associations:{
  	...
  	# 所有的embedded_associations
  	# 即所有的 cache_has_many :xxx, embed: true
  },
  normalized_has_many: [
  	...
  	# 所有的
  	# 即所有的 cache_has_many :xxx, embed: true
  ],
}
```
##### 实现
自己看源码解决

### record_from_coder
##### 功能
通过一个hash构建一个record，及其embedded_associations records

### resolve_cache_miss
##### 功能
看似最简单，却干了最多事的一个函数，identity_cache获取单条数据函数（fetch、fetch_by_id）当发现缓存中没有数据时与数据库交互的入口

##### 具体实现

### fetch_by_id

```
coder = IdentityCache.fetch(rails_cache_key(id)){ 
  coder_from_record(object = resolve_cache_miss(id)) 
}
object ||= record_from_coder(coder)
```
### fetch
fetch_by_id的找不到抛异常版本

### find_batch

```
#it behaves like ActiveRecord::Base.find_all_by_id

where('id IN (?)', ids).includes(cache_fetch_includes(options[:includes])).to_a
```

identity_cache获取多条记录时，当发现缓存中没有数据时与数据库交互的入口，返回对象中可能存在空对象


## dsl部分

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


david整理，这句话的意思是冤有头债有主。
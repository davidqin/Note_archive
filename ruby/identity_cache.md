
identity_cache
=======

一些基础
----
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

cache_has_many
--------

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

相当于向order model中注入以下方法

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


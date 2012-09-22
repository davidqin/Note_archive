module Check
  def self.included(base)
    base.extend ClassMethod
  end

  module ClassMethod
    def attr_check(name, &block)
      define_method "#{name}=" do |value|
	raise "invalid attribute" unless block.call(value)
        instance_variable_set("@#{name}", value)
      end

      define_method name do
	instance_variable_get("@#{name}")
      end
    end
  end
end

class Myclass
  include Check

  def self.ec
    class << self
      self
    end
  end

  attr_check :age do |v|
    v > 30
  end
end



class Pipeline
  attr_accessor :source

  def initialize
    @fiber = Fiber.new do
      process
    end
  end

  def |(other)
    other.source = self
    other
  end

  def process
    while value = input
      handle(value)
    end
  end

  def handle value
    output(value)
  end

  def resume
    @fiber.resume
  end

  def input
    source.resume
  end

  def output value
    Fiber.yield value
  end
end

class Producer < Pipeline
  def input
    gets.chomp
  end
end

class Consumer < Pipeline
  def output value
    puts value
  end
end

class Deco < Pipeline
  def handle value
    output("!!#{value}!!")
  end
end

produce = Producer.new
consumer = Consumer.new
deco = Deco.new

p = produce | deco | consumer
p.resume

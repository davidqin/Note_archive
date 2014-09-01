# coding: utf-8
require 'fiber'

def send(x)
  Fiber.yield x
end

def receiver producer
  producer.transfer
end

def producer
  Fiber.new do
    while true
      x = gets.chomp
      send(x)
    end
  end
end

def consumer(producer)
  while true
    x = receiver(producer)
    break if x == 'quit'
    puts x
  end
end

if $0 == __FILE__
  consumer(producer())
end

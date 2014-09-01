 #哲学家就餐问题
# 哲学家就餐问题是由Edsger Djisktra在1965年提出的，用来说明在多个进程为获得互斥性资源的使用权进行竞争时可能会出现哪些问题。

# 在这个问题中，五个哲学家正进行聚餐。他们坐在一个圆形餐桌周围，每个哲学家面前都有一碗米饭。另外还有五根筷子，每个哲学家一边一根。哲学家要花时间来思考人生的意义。无论何时只要他们饿了，他们就要试图吃饭。但是哲学家需要在每个手中都握有一根筷子才能弄到米饭吃。如果任何其他哲学家已经拿走了他所需要的两根筷子中的一根，那么这个饥饿的哲学家将会等待，直到那根被拿走的筷子可用为止。
class Chopstick
  def initialize
    @mutex = Mutex.new
  end

  def take
    @mutex.lock
  end

  def drop
    @mutex.unlock

  rescue ThreadError
    puts "Trying to drop a chopstick not acquired"
  end

  def in_use?
    @mutex.locked?
  end
end

class Table
  def initialize(num_seats)
    @chopsticks  = num_seats.times.map { Chopstick.new }
  end

  def left_chopstick_at(position)
    index = (position - 1) % @chopsticks.size
    @chopsticks[index]
  end

  def right_chopstick_at(position)
    index = (position + 1) % @chopsticks.size
    @chopsticks[index]
  end

  def chopsticks_in_use
    @chopsticks.select { |f| f.in_use? }.size
  end
end

class Philosopher
  def initialize(name)
    @name = name
  end

  def dine(table, position)
    @left_chopstick  = table.left_chopstick_at(position)
    @right_chopstick = table.right_chopstick_at(position)

    loop do
      think
      eat
    end
  end

  def think
    puts "#{@name} is thinking"
  end

  def eat
    take_chopsticks

    puts "#{@name} is eating."

    drop_chopsticks
  end

  def take_chopsticks
    @left_chopstick.take
    @right_chopstick.take
  end

  def drop_chopsticks
    @left_chopstick.drop
    @right_chopstick.drop
  end
end

names = %w{Heraclitus Aristotle Epictetus Schopenhauer Popper}

philosophers = names.map { |name| Philosopher.new(name) }
table        = Table.new(philosophers.size)

threads = philosophers.map.with_index do |philosopher, i|
  Thread.new { philosopher.dine(table, i) }
end

threads.each(&:join)
sleep
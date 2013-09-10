require 'benchmark'
require 'securerandom'
require 'zlib'

puts `ruby -v`
data = SecureRandom.hex(4096000)

def func1
  # puts "sleep 3 seconds in func1\n"
  sleep(0.1)
end

def func2
  # puts "sleep 2 seconds in func2\n"
  sleep(0.2)
end

def func3
  # puts "sleep 5 seconds in func3\n"
  sleep(0.3)
end

func1
func2
func3

Benchmark.bm do |b|
  b.report('1') do
    func1
    func2
    func3
  end

  b.report('2') do
    threads = []
    threads << Thread.new { func1 }
    threads << Thread.new { func2 }
    threads << Thread.new { func3 }
    threads.each {|t| t.join }
  end

  b.report('3') do
    16.times { Zlib::Deflate.deflate(data) }
  end

  b.report('4') do
    threads = []
    16.times do
      threads << Thread.new { Zlib::Deflate.deflate(data) }
    end
    threads.each {|t| t.join}
  end
end
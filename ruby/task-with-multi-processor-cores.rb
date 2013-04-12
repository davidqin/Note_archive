#!/usr/bin/ruby

# number of simultaneous processes
sim = 4

# array of elements to process
a = (1..100).to_a

# function that processes the data
def do_the_do i
  puts "starting #{i}"
  # do something, for example, sleep between 5 and 10 seconds
  #sleep(rand(5)+5)
  #sleep()
  puts "done #{i}"
end

# starting first N processes
sim.times do
  i = a.pop
	Process.fork {do_the_do(i)}
end

# start one by one as the previous finish
a.each do |i|
	Process.wait(0)
	Process.fork {do_the_do(i)}
end

# wait for all to finish
Process.waitall
puts "done all"

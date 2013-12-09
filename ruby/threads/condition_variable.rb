#有时候使用互斥（mutex ）来保护对临界数据的访问并不能满足要求，比如假设我们在一个临界区内，但是你还需要等待一个特殊的资源，如果你的线程这时候为了等待这个资源而休眠，可能会导致其它线程不能释放这个资源，因为它们都无法进入这个临界区，原来的线程一直在锁定着这个临界区。你也许需要暂时的放弃对临界区的控制，同时告诉其它线程你在等待某一资源。当这个资源可用之后，你的线程同时需要重新得到对临界区的控制权。

#条件变量正是用在此处。一个条件变量是一个简单的信号量，它关联一个特定的资源，在临界区的保护范围内使用。当你需要一个资源而这个资源暂时不可用的时候，你等待一个条件变量，这个操作将放弃对这个条件变量所在互斥（临界区？）的锁定。当其它线程发送信号告诉这个变量可用之后，原来的线程停止等待立即取得对临界区的锁定。

　

require 'thread'
mutex = Mutex.new
cv = ConditionVariable.new

a = Thread.new {
  mutex.synchronize {
    puts "A: I have critical section, but will wait for cv"
    cv.wait(mutex)
    puts "A: I have critical section again! I rule!"
  }
}

puts "(Later, back at the ranch...)"

b = Thread.new {
  mutex.synchronize {
    puts "B: Now I am critical, but am done with cv"
    cv.signal
    puts "B: I am still critical, finishing up"
  }
}
a.join
b.join
#结果：
#A: I have critical section, but will wait for cv(Later, back at the ranch...)

#B: Now I am critical, but am done with cv
#B: I am still critical, finishing up
#A: I have critical section again! I rule!
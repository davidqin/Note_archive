r, w = IO.pipe
m = Mutex.new
cv = ConditionVariable.new

write_t = Thread.start {
    loop do
        m.synchronize do
            cv.wait(m)
            w.puts "mother"
        end
        sleep 1
    end
}


read_t = Thread.start {
    m.synchronize do
        loop do
            puts r.gets
            cv.signal
        end
    end
}

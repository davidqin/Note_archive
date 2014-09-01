f = Fiber.new do
  1 + Fiber.yield
end

p f.resume(1)
p f.resume(2)

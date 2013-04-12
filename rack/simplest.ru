Simplest = proc { |env| ["200", {"Content-Type" => "text/plain"}, ["OK"]] }

run Simplest

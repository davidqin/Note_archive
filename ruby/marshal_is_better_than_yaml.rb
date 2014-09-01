require 'yaml'

hash = {:key1 => 'value1', :key2 => 'value2', :key3 => 'value3', :key4 => {:key41 => 'value41', :key41 => 'value42'}}

iterations = 10000

serialized_hash = nil

start = Time.now
1.upto(iterations) { serialized_hash = Marshal.dump(hash) }
puts "Marshal hash: #{Time.now - start} seconds"

start = Time.now
1.upto(iterations) { reloaded_hash = Marshal.load(serialized_hash) }
puts "Reload marshalled hash: #{Time.now - start} seconds"

start = Time.now
1.upto(iterations) { serialized_hash = hash.to_yaml }
puts "YAMLize hash: #{Time.now - start} seconds"

start = Time.now
1.upto(iterations) { reloaded_hash = YAML::load(serialized_hash) }
puts "Reload YAMLlized hash: #{Time.now - start} seconds"

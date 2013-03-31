class Tribble
  constructor: ->
    @isAlive = true
    Tribble.count++

  breed: -> new Tribble if @isAlive
  die: ->
    Tribble.count-- if @isAlive
    @isAlive = false

  @count: 0
  @makTrouble: -> console.log ('Trouble!' for i in [0..@count]).join(' ')

t1 = new Tribble
t2 = new Tribble

console.log Tribble
console.log Tribble.prototype
console.log t1

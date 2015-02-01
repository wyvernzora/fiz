chai = require('chai')
assert = chai.assert
should = chai.should()
expect = chai.expect
exec = require('child_process').exec
util = require 'util'

# Test target
target = './fiz -v'

# Convenience function for testing
run = (input, output, errmsg, callback) ->
  exec "echo \"#{input}\" | " + target, (error, stdout, stderr) ->
    try
      if output then expect(stdout.trim()).to.be.equal(output)
      if errmsg
        expect(stderr).to.contain(errmsg)
      else if errmsg is null
        expect(error).to.be.null()
        expect(stderr).to.have.length.of(0)
      callback()
    catch err
      callback(err)

describe '(inc exp)', ->

  it 'should increase a number by 1', (done) ->
    script = '(inc 1)'
    run script, '2', null, done

  it 'should increase an expression by 1', (done) ->
    script = '(inc (inc 1))'
    run script, '3', null, done

  it 'should panic when there are no arguments', (done) ->
    script = '(inc)'
    run script, null, 'INC expects 1 argument but got 0.', done

  it 'should panic when there are too many arguments', (done) ->
    script = '(inc 0 0)'
    run script, null, 'INC expects 1 argument but got 2.', done

describe '(dec exp)', ->

  it 'should decrease a number by 1', (done) ->
    script = '(dec 1)'
    run script, '0', null, done

  it 'should decrease an expression by 1', (done) ->
    script = '(dec (inc 0))'
    run script, '0', null, done

  it 'should panic when attempting to (dec 0)', (done) ->
    script = '(dec 0)'
    run script, null, 'Attempt to (dec 0).', done

  it 'should panic when there are no arguments', (done) ->
    script = '(dec)'
    run script, null, 'DEC expects 1 argument but got 0.', done

  it 'should panic when there are too many arguments', (done) ->
    script = '(dec 1 1)'
    run script, null, 'DEC expects 1 argument but got 2.', done

describe '(ifz exp0 exp1 exp2)', ->

  it 'should evaluate to exp1 when exp0 is not 0', (done) ->
    script = '(ifz 0 2 3)'
    run script, '2', null, done

  it 'should evaluate to exp2 when exp0 is 0', (done) ->
    script = '(ifz 1 2 3)'
    run script, '3', null, done

  it 'should panic when there are no arguments', (done) ->
    script = '(ifz)'
    run script, null, 'IFZ expects 3 arguments but got 0.', done

  it 'should panic when there are too few arguments', (done) ->
    script = '(ifz 1 2)'
    run script, null, 'IFZ expects 3 arguments but got 2.', done

  it 'should panic when there are too many arguments', (done) ->
    script = '(ifz 1 2 3 4)'
    run script, null, 'IFZ expects 3 arguments but got 4.', done

describe '(halt)', ->

  it 'should terminate program with "Halted." message', (done) ->
    script = '(halt)'
    run script, null, 'Halted.', done

  it 'should return syntax error when there are arguments', (done) ->
    script = '(halt 0)'
    run script, null, 'HALT expects no arguments but got 1.', done

describe '(define ...)', ->

  it 'should correctly parse argument list', (done) ->
    script = '(define (func a1 a2 a3 a4 a5) (inc 0))'
    run script, 'func = func; args = [a1 a2 a3 a4 a5 ]', '', done

  it 'should panic when there are no arguments', (done) ->
    script = '(define (func) (inc 0))'
    run script, null, 'syntax error', done

  it 'should panic when there are more than 10 arguments', (done) ->
    script = '(define (func a1 a2 a3 a4 a5 a6 a7 a8 a9 a10 a11))'
    run script, null, 'Number of arguments exceeds 10.', done

describe 'Test cases in the lab assignment', ->

  it '(inc (inc 5)) should result in 7', (done) ->
    script = '(inc (inc 5))'
    run script, '7', null, done

  it '(dec (inc (dec 3))) should result in 2', (done) ->
    script = '(dec (inc (dec 3)))'
    run script, '2', null, done

  it '(dec (ifz 0 4 (inc 1))) should result in 3', (done) ->
    script = '(dec (ifz 0 4 (inc 1)))'
    run script, '3', null, done

  it '(ifz 1 (halt) 5) should result in 5', (done) ->
    script = '(ifz 1 (halt) 5)'
    run script, '5', null, done


  it '(inc 4 5) should return syntax error', (done) ->
    script = '(inc 4 5)'
    run script, null, 'INC expects 1 argument but got 2.', done

  it '(ifz 0 halt) should return syntax error', (done) ->
    script = '(ifz 0 halt)'
    run script, null, 'IFZ expects 3 arguments but got 2.', done

  it '(inc (dec )) should return syntax error', (done) ->
    script = '(inc (dec ))'
    run script, null, 'DEC expects 1 argument but got 0.', done

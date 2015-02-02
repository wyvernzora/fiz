chai = require('chai')
assert = chai.assert
should = chai.should()
expect = chai.expect
exec = require('child_process').exec
util = require 'util'

# Test target
target = './fiz'

# Convenience function for testing
run = (flags, input, output, errmsg, callback) ->
  exec target + " #{flags} <<< \"#{input}\"", (error, stdout, stderr) ->
    try
      if output
        expect(stdout.replace(/\S*fiz>\S*/g, '').trim()).to.be.equal(output)
      if errmsg
        expect(stderr).to.contain(errmsg)
      else if errmsg is null
        expect(error).to.be.null()
        expect(stderr).to.have.length.of(0)
      callback()
    catch err
      callback(err)

describe ';comments', ->

  it 'should ignore comments on a separate line', (done) ->
    script = '''
    ;comments here
    (inc 1)
    '''
    run '-n -v', script, '2', null, done

  it 'should ignore comments on the same line', (done) ->
    script = '''
    (inc 1) ;comments here
    '''
    run '-n -v', script, '2', null, done

  it 'should ignore expression in the comments', (done) ->
    script = '''
    ;comments here (inc 1)
    (inc 2)
    '''
    run '-n -v', script, '3', null, done

describe '(inc exp)', ->

  it 'should increase a number by 1', (done) ->
    script = '(inc 1)'
    run '-n -v', script, '2', null, done

  it 'should increase an expression by 1', (done) ->
    script = '(inc (inc 1))'
    run '-n -v', script, '3', null, done

  it 'should panic when there are no arguments', (done) ->
    script = '(inc)'
    run '-n -v', script, null, 'INC expects 1 argument but got 0.', done

  it 'should panic when there are too many arguments', (done) ->
    script = '(inc 0 0)'
    run '-n -v', script, null, 'INC expects 1 argument but got 2.', done

describe '(dec exp)', ->

  it 'should decrease a number by 1', (done) ->
    script = '(dec 1)'
    run '-n -v', script, '0', null, done

  it 'should decrease an expression by 1', (done) ->
    script = '(dec (inc 0))'
    run '-n -v', script, '0', null, done

  it 'should panic when attempting to (dec 0)', (done) ->
    script = '(dec 0)'
    run '-n -v', script, null, 'Attempt to (dec 0).', done

  it 'should panic when there are no arguments', (done) ->
    script = '(dec)'
    run '-n -v', script, null, 'DEC expects 1 argument but got 0.', done

  it 'should panic when there are too many arguments', (done) ->
    script = '(dec 1 1)'
    run '-n -v', script, null, 'DEC expects 1 argument but got 2.', done

describe '(ifz exp0 exp1 exp2)', ->

  it 'should evaluate to exp1 when exp0 is not 0', (done) ->
    script = '(ifz 0 2 3)'
    run '-n -v', script, '2', null, done

  it 'should evaluate to exp2 when exp0 is 0', (done) ->
    script = '(ifz 1 2 3)'
    run '-n -v', script, '3', null, done

  it 'should panic when there are no arguments', (done) ->
    script = '(ifz)'
    run '-n -v', script, null, 'IFZ expects 3 arguments but got 0.', done

  it 'should panic when there are too few arguments', (done) ->
    script = '(ifz 1 2)'
    run '-n -v', script, null, 'IFZ expects 3 arguments but got 2.', done

  it 'should panic when there are too many arguments', (done) ->
    script = '(ifz 1 2 3 4)'
    run '-n -v', script, null, 'IFZ expects 3 arguments but got 4.', done

describe '(halt)', ->

  it 'should terminate program with "Halted." message', (done) ->
    script = '(halt)'
    run '-n -v', script, null, 'Halted.', done

  it 'should return syntax error when there are arguments', (done) ->
    script = '(halt 0)'
    run '-n -v', script, null, 'HALT expects no arguments but got 1.', done

describe '(define ...)', ->

  it 'should correctly parse argument list', (done) ->
    script = '(define (func a1 a2 a3 a4 a5) (inc 0))'
    run '-n -v', script, 'func = func; args = [a1 a2 a3 a4 a5 ]', '', done

  it 'should correctly parse function definition without arguments', (done) ->
    script = '(define (func) (inc 0))'
    run '-n -v', script, 'func = func; no-args', null, done

  it 'should correctly handle definition of up to 1000 functions', (done) ->
    script = ''
    script += "(define (f#{i} a b) (inc 0))\n" for i in [0...1000]
    run '-n -v', script, '', null, done

  it 'should correctly handle recursive definitions', (done) ->
    script = '''
    (define (add x y) (ifz y x (add (inc x) (dec y))))
    (add 1 2)
    '''
    run '-n', script, '3', null, done

  it 'should panic when the number of defined functions exceeds 1000', (done) ->
    script = ''
    script += "(define (f#{i} a b) (inc 0))\n" for i in [0..1000]
    run '-n -v', script, null, 'Number of defined functions exceeds 1000.', done

  it 'should panic when refefining an existing function', (done) ->
    script = '''
    (define (func a1) (inc 998))
    (define (func a1 a2) (dec 998))
    '''
    run '-n -v', script, null, 'Function \'func\' already defined.', done

  it 'should panic when function is defined with more than 10 arguments', (done) ->
    script = '(define (func a1 a2 a3 a4 a5 a6 a7 a8 a9 a10 a11))'
    run '-n -v', script, null, 'Number of arguments exceeds 10.', done

describe '(func ...)', ->

  it 'should correctly run a previously defined function', (done) ->
    script = '''
    (define (func a1) (inc 998))
    (func 0)
    '''
    run '-n -v', script, 'func = func; args = [a1 ]\n999', '', done

  it 'should correctly recognize variables within user-dfined functions', (done) ->
    script = '''
    (define (func a) (inc a))
    (func 999)
    '''
    run '-n ', script, '1000', null, done

  it 'should correctly call a user-defined function from within a user-defined function', (done) ->
    script = '''
    (define (fn0 a) (inc a))
    (define (fn1 b) (inc b))
    (fn0 (fn1 0))
    '''
    run '-n', script, '2', null, done

  it 'should panic when calling an undefined function', (done) ->
    script = '(func 0)'
    run '-n -v', script, null, 'Function \'func\' is undefined.', done

  it 'should panic when attempting to use an undefined variable', (done) ->
    script = '''
    (define (func a b) (inc x))
    (func 0 1)
    '''
    run '-n -v', script, null, 'Variable \'x\' is undefined.', done

  it 'should panic when function is called with less arguments than expected', (done) ->
    script = '''
    (define (func a b) (inc a))
    (func 1)
    '''
    run '-n -v', script, null, 'func expects 2 arguments but got 1', done

  it 'should panic when function is called with more arguments that expected', (done) ->
    script = '''
    (define (func a b) (inc a))
    (func 0 1 2)
    '''
    run '-n -v', script, null, 'func expects 2 arguments but got 3', done

  it 'should panic when function is called with more than 10 arguments', (done) ->
    script = '''
    (define (func a0 a1 a2 a3 a4 a5 a6 a7 a8a a9 a10) (inc 0))
    (func 1 2 3 4 5 6 7 8 9 10)
    '''
    run '-n', script, null, 'Number of arguments exceeds 10.', done

describe 'Test cases from the lab assignment', ->

  it '(inc (inc 5)) should result in 7', (done) ->
    script = '(inc (inc 5))'
    run '-n -v', script, '7', null, done

  it '(dec (inc (dec 3))) should result in 2', (done) ->
    script = '(dec (inc (dec 3)))'
    run '-n -v', script, '2', null, done

  it '(dec (ifz 0 4 (inc 1))) should result in 3', (done) ->
    script = '(dec (ifz 0 4 (inc 1)))'
    run '-n -v', script, '3', null, done

  it '(ifz 1 (halt) 5) should result in 5', (done) ->
    script = '(ifz 1 (halt) 5)'
    run '-n -v', script, '5', null, done


  it '(inc 4 5) should return syntax error', (done) ->
    script = '(inc 4 5)'
    run '-n -v', script, null, 'INC expects 1 argument but got 2.', done

  it '(ifz 0 halt) should return syntax error', (done) ->
    script = '(ifz 0 halt)'
    run '-n -v', script, null, 'Variable \'halt\' is undefined.', done

  it '(inc (dec )) should return syntax error', (done) ->
    script = '(inc (dec ))'
    run '-n -v', script, null, 'DEC expects 1 argument but got 0.', done

  it 'user-defined and recursive function', (done) ->
    script = '''
    (define (add x y) (ifz y x (add (inc x) (dec y))))
    (inc (add (add 1 2) 3))
    '''
    run '-n', script, '7', null, done

describe 'Regression testing for fixed issues', ->

  # Variables within user-defined function calls within user-defined function definitions are
  # sometimes incorrectly reported as undefined. An example reproduction of the issue is the
  # following test case.
  it 'issue #1: variables within user-defined function definitions are reported as undefined', (done) ->
    script = '''
    (define (f0 a) (inc a))
    (define (f1 b) (f0 (inc b)))
    '''
    run '-n', script, '', null, done

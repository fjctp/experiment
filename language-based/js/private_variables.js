"strict mode"

function foo () {
    test1 = "test 1"; // class variable
    var test2 = "test 2"; // local variable
    this.test3 = "test 3"; // instance variable
}
foo.prototype.show = function () {
    test1 += 1;
    console.log(test1);
    //console.log(test2); it does not exist
    
    this.test3 += 3;
    console.log(this.test3);
};
/*
foo.prototype.name = get name () {
    return test1;
}
*/

(function getter () {

}) ();

var a = new foo();
var b = new foo();
console.log('a:');
a.show();
console.log('b:');
b.show();

console.log('\n\na only');
console.log(a.test1);
console.log(a.test3);
//console.log(a.name);
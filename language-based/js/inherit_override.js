var util = require('util');

// super class
function obj1 (name) {
    this.firstname = name;
}
obj1.prototype.sayHello = function () {
    console.log('Hello');
    console.log(this.firstname);
};

// sub class
function obj2 (name, type) {
    obj1.call(this, name);
    this.type = type;
}
util.inherits(obj2, obj1);
(function testing () {
    var org = obj2.prototype.sayHello;
    obj2.prototype.sayHello = function () {
        org.call(this); // tell function org that thisArg
        console.log(this.type);
    };
}) ();

/*
(function () {
    var org = obj2.sayHello;
    console.log(org);
};
})();
*/

var a = new obj1('test');
a.sayHello();

var b = new obj2('test', 'type');
b.sayHello();
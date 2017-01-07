"strict mode"

function class_proper () {
    var Person = function(firstname) {
        this.firstName = firstname;
    };

    Person.prototype.sayHello = function () {
        console.log(this.firstName);
    };

    function Student (firstname, subject) {
        Person.call(this, firstname);
        this.subject = subject;
    };

    Student.prototype = Object.create(Person.prototype);
    Student.prototype.constructor = Student;
    Student.prototype.sayHello = function () {
        console.log(this.firstName);
        console.log(this.subject);
    }

    var student1 = new Student('J', '1');
    student1.sayHello();
};

function class_wrong () {
    var Person = function(firstname) {
        this.firstName = firstname;
    };

    Person.prototype.sayHello = function () {
        console.log(this.firstName);
    };

    var Student = function (firstname, subject) {
        this.subject = subject;
    };
    var Student.prototype = new Person.prototype;
    Student.prototype.sayHello = function () {
        console.log(this.firstName);
        console.log(this.subject);
    }

    var student1 = new Student('J', '1');
    student1.sayHello();
};

// work
console.log('Proper');
class_proper();
// not work
console.log('\nWrong');
class_wrong();
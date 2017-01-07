"strict mode"

function foo () {
    this.name = "John";
    this.type = "Student";
    this.a = 0;
}

(function () {
    //private function
    function add (tmp) {
        return ++tmp;
    }
    //private function
    function show (m) {
        console.log(m);
    }
    //public function
    foo.prototype.dosomething = function () {
        show(this.name);
        show(this.type);
        show(add(this.a));
    }
}) ();

var tt = new foo();
tt.dosomething();
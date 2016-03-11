var path = require('path');

var cwd = __dirname;
console.log('cwd: ' + cwd);
console.log('sep: ' + path.sep);

var cwd_array = cwd.split(path.sep);
console.log(cwd_array);

var cwd_pop = cwd_array.pop();
console.log(cwd_array);

console.log(cwd_array.toString());
var cwd_after = cwd_array.join(path.sep);
console.log('cwd_after: ' + cwd_after);
console.log('cwd_after: ' + path.join('D:','DATA','workplace'));
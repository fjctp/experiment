
package main

import "fmt"

// fibonacci is a function that returns
// a function that returns an int.
func fibonacci() func() int {
  var n0 = 0
  var n1 = 1
  return func() int {
    var tmp = n1
    n1 = n0 + n1
    n0 = tmp
    return n1
  }
}
func main() {
  f := fibonacci()
  for i := 0; i < 10; i++ {
    fmt.Println(f())
  }
}

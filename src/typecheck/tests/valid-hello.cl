class Main inherits IO {
  x : Int32 <- 34;

  main() : Object {
    {
      let a : Int64, b : Int64 <- 12, c : Float in {
        a <- b + let a : Int in { 4; };
      };
      out_string("Hi World!\n");
    }
  };
};

class Thing inherits IO {
  main() : Object {
    out_string("Hello, world!\n")
  };

  func(a : Bool, b : Float) : Int {
    a <- true
  };
};

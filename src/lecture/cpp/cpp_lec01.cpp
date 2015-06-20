#include <cstdlib>
#include <cstdio>
#include <cstring>

class Foo {
public:
  virtual void greet() { printf("Foo says hi\n"); }
  void me() { printf("Foo is best\n"); }
};

class Bar : public Foo {
public:
  virtual void greet() { printf("Bar says hi\n"); }
  virtual void dismiss() { printf("Bar says bye\n"); }
  void me() { printf("Bar is best\n"); }
};

class Baz : public Bar {
public:
  void dismiss() { printf("Baz says bye \n"); }
  void me() { printf("Baz is best\n"); }
};

int
main(int argc, char *argv[])
{
  Foo foo;
  Bar bar;
  Baz baz;
  Bar *barbaz = (Bar *)new Baz;

  foo.greet();
  puts("\n");

  bar.greet();
  bar.me();
  bar.dismiss();
  puts("\n");

  barbaz->me();
  barbaz->dismiss();

  return 0;
}


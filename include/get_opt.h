#ifndef _GET_OPT_H_
#define _GET_OPT_H 1_

class get_opt
{
public:
  static int get_options(int* arguments, int argc, char **argv);
  static void usage();
};

#endif /* _GET_OPT_H */
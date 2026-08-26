
#include <vector>
#include <string>
#include "StarterViewer.h"

using namespace starter;

int main( int argc, char** argv )
{

   StarterViewer* viewer = CreateViewer();

   std::vector<std::string> args;

   for(int i=0;i<argc;i++)
   {
      std::string s(argv[i]);
      args.push_back(s);
   }
   viewer->Init(args);

   viewer->MainLoop();

}

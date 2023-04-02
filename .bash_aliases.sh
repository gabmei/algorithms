#my-aliases
compile() { g++ -std=c++17 -Wall -Wextra -Wconversion -O2 -fsanitize=undefined -fsanitize=address -o "a.out" "$1"; }
run() { "./a.out"; }
crun() { compile "$1" && run; }
boilerplate(){
if [ ! -f "$1.cpp" ]
then
touch "$1.cpp"
cat << EOF > "$1.cpp"
#include<bits/stdc++.h>
using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  return 0;
}
EOF
fi
}

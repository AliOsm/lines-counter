#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <set>
#include <fstream>
#include <algorithm>
#include <dirent.h>

using namespace std;

set<string> exts;
queue<string> q;
map<string, int> files, lines;

string is_valid_d_name(string d_name) {
  string ext = "";
  for(int i = d_name.length() - 1; i >= 0; --i)
    if(d_name[i] == '.') {
      reverse(ext.begin(), ext.end());
      if(exts.count(ext) == 1)
        return ext;
      else
        return "-";
    } else
      ext += d_name[i];
  return "-";
}

int count_lines(string file_path) {
  int ret = 0;
  ifstream file(file_path);
  string tmp;
  while(file >> tmp)
    ++ret;
  file.close();
  return ret;
}

int main(int argc, char* argv[]) {
  if(argc < 2) {
    cerr << "Usage: " << argv[0] << " PATH EXT [EXT [EXT [...]]]" << endl;
    return EXIT_FAILURE;
  }

  for(int i = 2; i < argc; ++i) {
    exts.insert(argv[i]);
    files[argv[i]] = 0;
    lines[argv[i]] = 0;
  }

  string path = argv[1];

  if(path.back() == '/')
    path.pop_back();

  DIR *dir;
  struct dirent *ent;
  
  q.push(path);
  while(!q.empty()) {
    string cur_path = q.front();
    q.pop();

    if((dir = opendir(cur_path.c_str())) != NULL) {
      while((ent = readdir(dir)) != NULL) {
        string d_name = ent->d_name;

        if(d_name == ".." || d_name == ".")
          continue;

        if(ent->d_type == DT_DIR) {
          q.push(cur_path + "/" + d_name);
        } else if(ent->d_type == DT_REG) {
          string cur_ext = is_valid_d_name(d_name);
          if(cur_ext != "-") {
            // cout << d_name << endl;
            lines[cur_ext] += count_lines(cur_path + "/" + d_name);
            ++files[cur_ext];
          }
        }
      }

      closedir(dir);
    }
  }

  int total_files = 0, total_lines = 0;

  for(set<string>::iterator it = exts.begin(); it != exts.end(); ++it) {
    cout << *it << " extension:" << endl;
    cout << "Number of files: " << files[*it] << endl;
    cout << "Number of lines: " << lines[*it] << endl;
    cout << endl;
    total_files += files[*it];
    total_lines += lines[*it];
  }

  cout << "Total number of files is " << total_files << endl;
  cout << "Total number of lines is " << total_lines << endl;

  return 0;
}

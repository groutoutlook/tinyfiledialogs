// Helper on those functions.
#include "tinyfiledialogs.h"
#include <string>
#include <vector>
#include <filesystem>

namespace tfd {
 auto openFile(
   const std::string& title,
	 const std::filesystem::path& defaultPath = std::filesystem::current_path(),
   const std::vector<std::string>& patterns = {".txt",".cpp"},
   const std::string& fileDescription = "Default description.",
   const bool allowMultipleSelect = false
 ) -> std::string {

   // INFO: Convert patterns to a format compatible with tinyfd_openFileDialog
   std::vector<const char*> cPatterns;
   for (const auto& pattern : patterns) {
     cPatterns.push_back(pattern.c_str());
   }

   auto ret = tinyfd_openFileDialog(
     title.c_str(),
     defaultPath.string().c_str(),
     static_cast<int>(cPatterns.size()),
     cPatterns.empty() ? nullptr : cPatterns.data(),
     fileDescription.empty() ? nullptr : fileDescription.c_str(),
     allowMultipleSelect ? 1 : 0
   );

   return ret ? std::string(ret) : "";
 }

 // INFO: open folder, since it couldnt be multiple select, I think it's safe to put it as return one path.
 auto openFolder(
   const std::string& title,
   const std::filesystem::path& defaultPath = std::filesystem::current_path()
 ) -> std::filesystem::path {

   auto ret = tinyfd_selectFolderDialog(
     title.c_str(),
     defaultPath.string().c_str()
   );

   return std::filesystem::path(ret ? std::string(ret) : "./");
 }
}

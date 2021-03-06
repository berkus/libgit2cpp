#include "git2cpp/status.h"
#include "git2cpp/error.h"

namespace git
{
    size_t Status::entrycount() const
    {
        return git_status_list_entrycount(status_);
    } 

    git_status_entry const & Status::operator[] (size_t i) const
    {
        if (auto res = git_status_byindex(status_, i))
            return *res;
        else
            throw error_t("status entry index out of bounds: " + std::to_string(i));
    }

    Status::Status(git_repository * repo, git_status_options const & opts)
    {
        if (git_status_list_new(&status_, repo, &opts))
            throw get_status_error();
    }

    Status::~Status()
    {
        git_status_list_free(status_);
    }
}


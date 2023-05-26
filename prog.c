#include <git2/errors.h>
#include <git2/global.h>
#include <git2/repository.h>
#include <git2/sys/repository.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
  int error;

  int i, disable_owner_validation = 0;
  char *repo_path = NULL;

  for (i = 1; i < argc; i++) {
    char *arg = argv[i];
    if (strcmp(arg, "--disable-owner-validation") == 0) {
      disable_owner_validation = 1;
    } else {
      repo_path = arg;
    }
  }

  if (repo_path == NULL) {
    fprintf(stderr, "usage: %s [--disable-owner-validation] <repo>\n", argv[0]);
    return 2;
  }

  if (disable_owner_validation) {
    git_libgit2_opts(GIT_OPT_SET_OWNER_VALIDATION, 0);
    if (error != 0) {
      const git_error *err = git_error_last();
      fprintf(stderr, "failed to disable owner validation: %s\n", err->message);
      return 1;
    }
  }

  git_repository *repo;
  git_buf repository_path = {NULL};

  git_libgit2_init();

  error = git_repository_discover(&repository_path, repo_path, 0, NULL);
  if (error != 0) {
    const git_error *err = git_error_last();
    fprintf(stderr, "failed to discover repository: %s\n", err->message);
    return 1;
  }

  error = git_repository_open(&repo, repository_path.ptr);

  if (error != 0) {
    const git_error *err = git_error_last();
    fprintf(stderr, "failed to open repository: %s\n", err->message);
    return 1;
  }

  git_buf_dispose(&repository_path);
  git_libgit2_shutdown();

  return 0;
}

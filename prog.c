#include <git2/errors.h>
#include <git2/global.h>
#include <git2/repository.h>
#include <git2/sys/repository.h>
#include <stdio.h>

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("usage: %s <repo>\n", argv[0]);
    return 2;
  }

  int error;
  git_repository *repo;
  git_buf repository_path = {NULL};

  git_libgit2_init();

  error = git_repository_discover(&repository_path, argv[1], 0, NULL);
  if (error != 0) {
    const git_error *err = git_error_last();
    printf("ERROR: %s\n", err->message);
    return 1;
  }

  error = git_repository_open(&repo, repository_path.ptr);

  if (error != 0) {
    const git_error *err = git_error_last();
    printf("ERROR: %s\n", err->message);
    return 1;
  }

  git_buf_dispose(&repository_path);
  git_libgit2_shutdown();

  return 0;
}

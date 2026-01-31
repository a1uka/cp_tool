#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define MEM_SIZE 64

int main(int argc, char *argv[]) {
	char memory[MEM_SIZE];
	printf("%s: copying file ...\n", argv[0]);
	if (argc == 1) {
		printf("%s: missing file operand\n", argv[0]);
		return 0;
	}
	if (argc == 2) {
		printf("%s: missing destination file operand after '%s'\n", argv[0], argv[1]);
		return 0;
	}

	struct stat stack_stat;
	int bytes_read;
	int src_file_desc, target_file_desc, dir_file_desc;

	if (argc == 3) {
		stat(argv[1], &stack_stat);


		src_file_desc = open(argv[1], O_RDONLY, 0);
		target_file_desc = creat(argv[2], stack_stat.st_mode);


		while ((bytes_read = read(src_file_desc, memory, MEM_SIZE)) > 0) {
			write(target_file_desc, memory, bytes_read);
		}
	}
	else {
		for (int i = 1; i < argc - 1; i++) {
			src_file_desc = open(argv[i], O_RDONLY, 0);
			dir_file_desc = open(argv[argc - 1], O_RDONLY, 0);
			stat(argv[i], &stack_stat);
			target_file_desc = openat(dir_file_desc, argv[i], O_CREAT | O_WRONLY | O_TRUNC, stack_stat.st_mode);

			while ((bytes_read = read(src_file_desc, memory, MEM_SIZE)) > 0) {
				write(target_file_desc, memory, bytes_read);
			}
		}
	}
	

	return 0;
}
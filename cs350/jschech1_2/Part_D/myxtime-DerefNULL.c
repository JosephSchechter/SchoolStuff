#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
MODULE_LICENSE("DUAL BSD/GPL");


int my_xtime_read(char * sbuffer, 
		char ** my_buffer, 
		off_t file_pos, 
		int my_buffer_length, 
		int *eof, 
		void * data)
{
	if(file_pos > 0){
		return 0;
	}
	
	int length;
	static char mybuf[512];
	struct timespec ret = current_kernel_time();
	
	
	length = sprintf(mybuf, "%ld  %ld\n", ret.tv_sec, ret.tv_nsec);
	
	*my_buffer = mybuf;
	
	return length;

}


// called when module is installed
int __init init_module()
{
	struct proc_dir_entry * pde;
	printk("myxtime module: Hello World!\n");
	pde = create_proc_read_entry("myxtime", 0, NULL, my_xtime_read, NULL);
	
	int * iptr = NULL;
	static char zstring[512];
	sprintf(zstring, "Dereferencing a Null pointer: %d\n", *iptr);
	
	

	return 0;
	//return -1;
}



// called when module is removed
void __exit cleanup_module()
{
	printk("myxtime module: Goodbye, cruel world!!\n");
	remove_proc_entry("myxtime", NULL);
}



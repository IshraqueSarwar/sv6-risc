# include <stdarg.h>
# include "uart.h"



static void printint(long num, int base, int sign){
	char buff[32];
	int i = 0;
	unsigned int n;
	// here  we're just converting the number into neg if sign is needed
	if(sign && num<0){
		n = -num;
	}else{
		n = num;
		sign = 0;
	}

	// we fill out the buffer here
	if(n == 0){
		buff[i++] = '0';
	}else{
		while(n>0){
			int d = n%base;

			if(d<10){
				buff[i++] = '0'+d;
			}else{
				buff[i++] = 'a'+d-10;
			}

			n/=base;
		}
	}

	// we add the negative sign if its required
	if(sign)buff[i++]='-';


	// we finally print the chars stored in buffer
	while(i-- >=0){
		uart_putc(buff[i]);
	}
}



//static void printhex(){
//}



void kprintf(const char *fmt, ...){
	va_list arg_ptr;
	va_start(arg_ptr, fmt);

	for(const char *p = fmt; *p;p++){
		if(*p != '%'){
			uart_putc(*p);
			continue;
		}
		p++;

		switch(*p){
			case 'd':
				printint(va_arg(arg_ptr, int), 10, 1);
				break;
			case 'x':
				printint(va_arg(arg_ptr, unsigned int), 16, 0);
				break;
			case 's':{
				const char *s = va_arg(arg_ptr, const char*);
				if(!s)s="(null)";
				while(*s){
					uart_putc(*s++);
				}
				break;
			}
			case '%':
				uart_putc('%');
				break;
			default:
				uart_putc('%');
				uart_putc(*p);		
		}
	
	}

	va_end(arg_ptr);
	

}

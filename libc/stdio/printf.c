#include <stdint.h>
#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>

#include <stdio.h>
#include <string.h>

static bool print(const char* data, size_t length) {
	const unsigned char* bytes = (const unsigned char*) data;
	for (size_t i = 0; i < length; i++)
		if (putchar(bytes[i]) == EOF)
			return false;
	return true;
}

static bool printHexDigit(const char hex) {
	switch (hex & 0x0F) {
		case 0x00: return print("0", 1);
		case 0x01: return print("1", 1);
		case 0x02: return print("2", 1);
		case 0x03: return print("3", 1);
		case 0x04: return print("4", 1);
		case 0x05: return print("5", 1);
		case 0x06: return print("6", 1);
		case 0x07: return print("7", 1);
		case 0x08: return print("8", 1);
		case 0x09: return print("9", 1);
		case 0x0A: return print("A", 1);
		case 0x0B: return print("B", 1);
		case 0x0C: return print("C", 1);
		case 0x0D: return print("D", 1);
		case 0x0E: return print("E", 1);
		case 0x0F: return print("F", 1);
		default: return false;
	}
}

static bool printHex(const uint32_t hex) {
	print("0x", 2);
	if (!printHexDigit((char)((hex & 0xF0000000) >> 28)))
		return false;
	if (!printHexDigit((char)((hex & 0x0F000000) >> 24)))
		return false;
	if (!printHexDigit((char)((hex & 0x00F00000) >> 20)))
		return false;
	if (!printHexDigit((char)((hex & 0x000F0000) >> 16)))
		return false;
	if (!printHexDigit((char)((hex & 0x0000F000) >> 12)))
		return false;
	if (!printHexDigit((char)((hex & 0x00000F00) >>  8)))
		return false;
	if (!printHexDigit((char)((hex & 0x000000F0) >>  4)))
		return false;
	if (!printHexDigit((char)((hex & 0x0000000F)      )))
		return false;
	return true;
}

int printf(const char* restrict format, ...) {
	va_list parameters;
	va_start(parameters, format);

	int written = 0;

	while (*format != '\0') {
		size_t maxrem = INT_MAX - written;

		if (format[0] != '%' || format[1] == '%') {
			if (format[0] == '%')
				format++;
			size_t amount = 1;
			while (format[amount] && format[amount] != '%')
				amount++;
			if (maxrem < amount) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(format, amount))
				return -1;
			format += amount;
			written += amount;
			continue;
		}

		const char* format_begun_at = format++;

		if (*format == 'c') {
			format++;
			char c = (char) va_arg(parameters, int /* char promotes to int */);
			if (!maxrem) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(&c, sizeof(c)))
				return -1;
			written++;
		} else if (*format == 's') {
			format++;
			const char* str = va_arg(parameters, const char*);
			size_t len = strlen(str);
			if (maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(str, len))
				return -1;
			written += len;
		} else if (format[0] == '#' && format[1] == '0' && format[2] == '8' && format[3] == 'X') {
			format += 4;
			size_t len = 10;
			if (maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			const uint32_t value = va_arg(parameters, uint32_t);
			if (!printHex(value))
				return -1;
			written += len;
		} else {
			format = format_begun_at;
			size_t len = strlen(format);
			if (maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(format, len))
				return -1;
			written += len;
			format += len;
		}
	}

	va_end(parameters);
	return written;
}

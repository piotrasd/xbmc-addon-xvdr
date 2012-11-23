// WINDOWS
#ifdef WIN32

#define syslog(s, msg, ...) std::cout << msg << std::endl;
#define _WIN32_WINNT 0x0501
#define SHUT_RDWR SD_BOTH
#define sockerror() WSAGetLastError()

#define EINPROGRESS WSAEINPROGRESS
#define SEWOULDBLOCK WSAEWOULDBLOCK
#define ENOTSOCK WSAENOTSOCK
#define ECONNRESET WSAECONNRESET

#define sockval_t char
#define sendval_t const char

#define MSG_DONTWAIT 0
#define MSG_NOSIGNAL 0

#include <iostream>
#include <winsock2.h>
#include <ws2spi.h>
#include <ws2tcpip.h>

#include "pthreads-win32/pthread.h"

uint32_t htobe32(uint32_t u);
uint64_t htobe64(uint64_t u);
uint16_t htobe16(uint16_t u);
uint32_t be32toh(uint32_t u);
uint64_t be64toh(uint64_t u);
uint16_t be16toh(uint16_t u);

// LINUX / OTHER
#else

#ifdef __FreeBSD__
#include <sys/types.h>
#include <sys/endian.h>
#include <netinet/in.h>
#endif

#define INVALID_SOCKET -1
#define SEWOULDBLOCK EAGAIN

#define closesocket close
#define sockerror() errno

#define sockval_t int*
#define sendval_t const void

#include <fcntl.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include <netinet/tcp.h>
#include <syslog.h>
#include <signal.h>
#include <pthread.h>
#endif

#ifdef __APPLE__
#define MSG_NOSIGNAL 0
#include <libkern/OSByteOrder.h>
#define be64toh(x) (unsigned long long) OSSwapBigToHostInt64((uint64_t)x)
#define be32toh(x) (unsigned long) OSSwapBigToHostInt32((uint32_t)x)
#define be16toh(x) (unsigned short) OSSwapBigToHostInt16((uint16_t)x)
#define htobe64(x) (unsigned long long) OSSwapHostToBigInt64((uint64_t)x)
#define htobe32(x) (unsigned long) OSSwapHostToBigInt32((uint32_t)x)
#define htobe16(x) (unsigned short) OSSwapHostToBigInt16((uint16_t)x)
#endif

// ANDROID
#ifdef ANDROID
#include <linux/in.h>
#ifndef __BSD_VISIBLE
#define __BSD_VISIBLE
#endif
#include <sys/endian.h>
#define be16toh betoh16
#define be32toh betoh32
#define be64toh betoh64
#endif

bool pollfd(int fd, int timeout_ms, bool in);
bool setsock_nonblock(int fd, bool nonblock = true);
void setsock_keepalive(int fd);
int socketread(int fd, uint8_t* data, int datalen, int timeout_ms);

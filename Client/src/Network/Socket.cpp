#include <string.h>

#include "Serializable.h"
#include "Socket.h"
#include <unistd.h>

Socket::Socket(const char *address, const char *port) : sd(-1)
{
    // Construir un socket de tipo AF_INET y SOCK_DGRAM usando getaddrinfo.
    // Con el resultado inicializar los miembros sd, sa y sa_len de la clase
    struct addrinfo hints;
    struct addrinfo *result;
    int errorCode;

    memset((void*) &hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;

    errorCode = getaddrinfo(address, port, &hints, &result);
    if (errorCode)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(errorCode));
        exit(EXIT_FAILURE);
    }

    sd = socket(result->ai_family, result->ai_socktype, 0);
    sa = *result->ai_addr;
    sa_len = result->ai_addrlen;
    if (sd == -1)
        exit(EXIT_FAILURE);

    freeaddrinfo(result);
}

Socket::~Socket()
{
    ::close(sd);
}

char* Socket::recv(Socket *&sock)
{
    struct sockaddr sa;
    socklen_t sa_len = sizeof(struct sockaddr);

    char *buffer = (char*)malloc(sizeof(char) * MAX_MESSAGE_SIZE);

    ssize_t bytes = ::recvfrom(sd, buffer, MAX_MESSAGE_SIZE, 0, &sa, &sa_len);

    if (bytes <= 0)
    {
        return nullptr;
    }

    if (sock != 0)
    {
        sock = new Socket(&sa, sa_len);
    }

    return buffer;
}

int Socket::send(Serializable &obj, const Socket &sock)
{
    // Serializar el objeto
    // Enviar el objeto binario a sock usando el socket sd
    obj.to_bin();
    return ::sendto(sd, obj.data(), obj.size(), 0, &sock.sa, sock.sa_len);
}

bool operator==(const Socket &s1, const Socket &s2){
    // Comparar los campos sin_family, sin_addr.s_addr y sin_port
    // de la estructura sockaddr_in de los Sockets s1 y s2
    // Retornar false si alguno difiere

    struct sockaddr_in *s1_addr = (struct sockaddr_in *)&s1.sa;
    struct sockaddr_in *s2_addr = (struct sockaddr_in *)&s2.sa;

    return s1_addr->sin_family == s2_addr->sin_family &&
           s1_addr->sin_addr.s_addr == s2_addr->sin_addr.s_addr &&
           s1_addr->sin_port == s2_addr->sin_port;
};

std::ostream &operator<<(std::ostream &os, const Socket &s)
{
    char host[NI_MAXHOST];
    char serv[NI_MAXSERV];

    getnameinfo((struct sockaddr *)&(s.sa), s.sa_len, host, NI_MAXHOST, serv,
                NI_MAXSERV, NI_NUMERICHOST);

    os << host << ":" << serv;

    return os;
};

void Socket::close()
{
    ::shutdown(sd, SHUT_RDWR);
    ::close(sd);
}
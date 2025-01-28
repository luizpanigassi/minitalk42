# 42minitalk
A project on sending messages using UNIX code!

This was an interesting one. I've seen bitwise operators before,
when studying radix for push_swap, but now it's actually for something useful.
So, for this one, we need to start a server to receive input and create a program
which will act as a client, sending those messages bit by bit (literal bits, not
small parts).

It's all about using SIGUSR. SIGUSR1 will send 0s, 2 will send 1s. Simple, right? Right.
First, when the server is initialized, a PID will be generated, which will be used by the client
to send the messages. When the server receives a signal, a sigaction will be conducted, translating the
signal. When 8 signals (bits, in this case) are received, the program will translate that into a char,
and keep going until the signals stop. As a reaction, the server will send a kill signal to
the client, which will indicate that the bit was received and it's ready to get another one,
and so on until the end. On the client side, a global variable will control this signal received
so it won't overflood the server with signals, corrupting the message. So the bit will be sent,
the bit received flag will be changed, and when the server the signal, it will be changed back
and the cycle continues until the end of the message. The PID must be entered by the user, which
will be converted to a char so it can be used to send the message, thus making everything work like
magic. Lots of SIGUSR1 and 2s will be sent, the message will be transmitted, and people will be happy.

For the bonus, I've worked on coverting everything to UTF-8, which can handle emojis and weird characters.
Apparently it was REALLY overkill and I added a whole bunch of not so useful things, but it works. I convert
the characters to wchars (wide chars) which can sustain the size of emojis. You can check if you want, but
apparently it was really overkill. Still works though.

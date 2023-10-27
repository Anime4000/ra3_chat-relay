# Red Alert 3 Chat Relay
Online gaming enthusiasts, especially fans of the classic Red Alert 3 game, may encounter a common challenge: their Internet Service Providers (ISPs) blocking the essential TCP port 6667, preventing them from enjoying multiplayer gameplay.

This article is a comprehensive guide on how to bypass the ISP-imposed block on TCP port 6667 specifically for the Red Alert 3 game. It explores various methods and solutions to regain access to this port, ensuring that gamers can connect with friends and fellow players worldwide. The guide covers techniques such as VPN (Virtual Private Network) usage and port forwarding, offering step-by-step instructions to help players overcome this restriction.

By following the recommendations in this article, Red Alert 3 gamers can ensure uninterrupted access to the online multiplayer experience, fostering the vibrant and competitive gaming community that has continued to thrive around this beloved real-time strategy title.

# Compile
This code should be compile on Linux (Ubuntu) Server

```
gcc -static -o ra3-chat_relay ra3-chat_relay.c
```

# Run
Before run, make sure the `ra3-chat_relay` has executable bit

Then can run the `ra3-chat_relay` via `screen`:
```
screen -mdSU ra3 ./ra3-chat_relay
```

To see the log
```
screen -r ra3
```

To Exit the `screen` press
```
CTRL+A+D
```

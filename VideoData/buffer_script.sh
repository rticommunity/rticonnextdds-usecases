sudo sysctl -w net.core.rmem_default="65536"
sudo sysctl -w net.core.wmem_default="65536"
sudo sysctl -w net.core.rmem_max="5000000"
sudo sysctl -w net.core.wmem_max="5000000"

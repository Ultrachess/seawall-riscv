TOOLCHAIN_TAG := 0.11.0
TOOLCHAIN_IMG := cartesi/toolchain:$(TOOLCHAIN_TAG)
CONTAINER_NAME := ctsi-riscv-build
CONTAINER_BASE := /opt/ctsi-riscv-build
TARGET_DIR := target
CONTAINER_TARGET_DIR:= /opt/ctsi-riscv-build/seawall

$(TARGET_DIR) &:
	@if docker inspect $(CONTAINER_NAME) > /dev/null 2>&1; then \
		docker rm -f $(CONTAINER_NAME) > /dev/null; \
	fi
	@docker run -w $(CONTAINER_BASE) -i -d --name $(CONTAINER_NAME) $(TOOLCHAIN_IMG) bash
	
	@docker cp . $(CONTAINER_NAME):$(CONTAINER_BASE)
	@docker exec $(CONTAINER_NAME) ls
	@docker exec $(CONTAINER_NAME) riscv64-cartesi-linux-gnu-g++ seawall.cc -pthread -std=c++17 -o seawall
	@docker cp $(CONTAINER_NAME):$(CONTAINER_TARGET_DIR) seawall
	@docker rm -f $(CONTAINER_NAME) > /dev/null
	@echo "$(TARGET_DIR): OK"
	


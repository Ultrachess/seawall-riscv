TOOLCHAIN_TAG := 0.12.0
TOOLCHAIN_IMG := cartesi/toolchain:$(TOOLCHAIN_TAG)
CONTAINER_NAME := ctsi-riscv-build
CONTAINER_BASE := /opt/ctsi-riscv-build
TARGET_DIR := target
CONTAINER_TARGET_DIR:= /opt/ctsi-riscv-build/seawall
UPX_IMG := quay.io/kkh913/upx:latest

$(TARGET_DIR) &:
	@if docker inspect $(CONTAINER_NAME) > /dev/null 2>&1; then \
		docker rm -f $(CONTAINER_NAME) > /dev/null; \
	fi
	@docker run -w $(CONTAINER_BASE) -i -d --name $(CONTAINER_NAME) $(TOOLCHAIN_IMG) bash
	
	@docker cp . $(CONTAINER_NAME):$(CONTAINER_BASE)
	@docker exec $(CONTAINER_NAME) ls
	@docker exec $(CONTAINER_NAME) riscv64-cartesi-linux-gnu-g++ seawall.cc -pthread -std=c++17 -o seawall
	@docker cp $(CONTAINER_NAME):$(CONTAINER_TARGET_DIR) seawall

	# Stop and remove the container
	@docker stop $(CONTAINER_NAME) > /dev/null
	@docker rm -f $(CONTAINER_NAME) > /dev/null

	# # UPX compression using Docker
	# @echo "Compressing seawall binary with UPX using Docker..."
	# @docker run --rm -w "$(shell pwd)" -v "$(shell pwd):$(shell pwd)" $(UPX_IMG) --best --lzma -o seawall-compressed seawall
	# @mv seawall-compressed seawall
	# @echo "Compression complete."

	@echo "$(TARGET_DIR): OK"


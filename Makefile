# コンパイラとフラグの定義
CXX := g++
CXXFLAGS := -Wall -Werror -Wextra -pedantic-error -std=c++98
LDFLAGS :=
INCLUDES := -Iincludes

# ソースファイルとオブジェクトファイルの定義
COMMON_SRCS := $(wildcard srcs/Socket.cpp srcs/config.cpp)
COMMON_OBJS := $(COMMON_SRCS:srcs/%.cpp=objs/%.o)
SERVER_SRCS := srcs/server.cpp
CLIENT_SRCS := srcs/client.cpp
SERVER_OBJS := $(SERVER_SRCS:srcs/%.cpp=objs/%.o)
CLIENT_OBJS := $(CLIENT_SRCS:srcs/%.cpp=objs/%.o)
DEPS := $(OBJS:.o=.d)

# 実行ファイルの名前
SERVER := server
CLIENT := client

# デフォルトターゲット
all: $(SERVER) $(CLIENT)

# サーバーとクライアントのビルド
$(SERVER): $(SERVER_OBJS) $(COMMON_OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@

$(CLIENT): $(CLIENT_OBJS) $(COMMON_OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@

# オブジェクトファイルのビルドルール
objs/%.o: srcs/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

# 依存関係ファイルのインクルード
-include $(DEPS)

# クリーンルール
clean:
	$(RM) $(SERVER) $(CLIENT) $(OBJS) $(DEPS)

fclean: clean
	$(RM) $(SERVER) $(CLIENT)

re: fclean all

.PHONY: all clean fclean re

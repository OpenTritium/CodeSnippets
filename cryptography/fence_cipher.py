import argparse
from math import ceil


def encrypt(clear_text: str, size: int) -> str:
    """
    加密函数
    :param clear_text: 明文字符串
    :param size: 栅栏大小
    :return: 加密字符串
    """
    # 补齐空格才能被完整分组
    expanded_string = clear_text.ljust(size * ceil(len(clear_text) / size))
    # 使用列表推导式将字符串切片生成新列表
    raw_list = [expanded_string[i:i + size] for i in range(0, len(expanded_string), size)]
    # 开始分组
    cipher_list = [item[i] for i in range(size) for item in raw_list]
    # 转换到字符串
    return "".join(cipher_list)


def decrypt(cipher_text: str, size: int) -> str:
    """
    解密函数
    :param cipher_text: 密文
    :param size: 栅栏大小
    :return: 解密结果
    """
    # 补齐空格才能被完整分组
    expanded_string = cipher_text.ljust(size * ceil(len(cipher_text) / size))
    # 计算每列包含多少个字符
    column_len = len(expanded_string) // size
    # 生成 size 列 column_size 长的字符串组
    cipher_list = [expanded_string[i:i + column_len] for i in range(0, len(expanded_string), column_len)]
    # 再从这些组中依次取元素
    clear_list = [item[i] for i in range(column_len) for item in cipher_list]
    # 会自动去除空格
    return "".join(clear_list)


def violent_crack(cipher_text: str) -> str:
    """
    填充的空格数取决于栅栏大小
    设栅栏大小为 n
    填充空格的数量范围则是 [0,n-1]
    栅栏大小与明文长度的关系是
    n 属于 [2,size)
    :param cipher_text: 密文
    :return: 破解结果
    """
    for n in range(2, len(cipher_text)):
        for space_num in range(0, n):
            guess_string = cipher_text.ljust(len(cipher_text) + space_num)
            # 返回迭代器对象
            yield decrypt(guess_string, n)


def args_parser():
    parser = argparse.ArgumentParser()
    parser.add_argument("--input", "-i", required=True, type=str, help="输入数据")
    parser.add_argument("--size", "-s", type=int, help="栅栏大小")
    parser.add_argument("--encrypt", "-e", action="store_true", help="带上此参数则启用加密，否则默认为解密")
    parser.add_argument("--crack", "-c", action="store_true", help="是否启用暴力破解")
    args = parser.parse_args()
    # 输入数据
    input_data = args.input
    # 是否加密
    is_encrypt = args.encrypt
    # 栅栏大小
    fence_size = args.size
    # 是否暴力破解
    is_crack_mode = args.crack

    if is_crack_mode:
        for index, elem in enumerate(violent_crack(input_data)):
            print(f"第 {index + 1} 轮暴力破解结果 {elem}")
    else:
        if is_encrypt:
            print(f"加密结果为 {encrypt(input_data, fence_size)}")
        else:
            print(f"解密结果为 {decrypt(input_data, fence_size)}")


args_parser()

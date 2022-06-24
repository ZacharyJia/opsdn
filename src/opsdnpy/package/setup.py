import setuptools


with open("README.md", "r") as fh:
    long_description = fh.read()

setuptools.setup(
    name="opsdnpy",
    version="0.1.3",
    author="Jia Zequn",
    author_email="zachary@bjtu.edu.cn",
    description="A python package for OPSDN",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="https://github.com/ZacharyJia/opsdnpy",
    packages=setuptools.find_packages(),
    classifiers=[
        "Programming Language :: Python :: 3",
        "Operating System :: OS Independent",
    ],
    install_requires=[
        "ryu==4.34",
        "networkx==2.8.2"
    ],
    license="Apache 2.0"
)

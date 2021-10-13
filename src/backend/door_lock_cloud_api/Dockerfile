FROM python:3.7-buster

RUN pip install --upgrade pip

RUN apt update \
    && apt install -y apt-utils gcc g++ 

ADD ./requirements.txt /door-look-cloud-api/requirements.txt

WORKDIR /door-look-cloud-api

RUN pip install -r requirements.txt

COPY . /door-look-cloud-api

EXPOSE 5001

CMD python ./src/server.py
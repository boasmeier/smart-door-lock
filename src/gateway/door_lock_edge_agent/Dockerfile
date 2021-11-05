FROM python:3.7-buster

RUN pip install --upgrade pip

ADD ./requirements.txt /door-look-cloud-agent/requirements.txt

WORKDIR /door-look-cloud-agent

RUN pip install -r requirements.txt

COPY . /door-look-cloud-agent

CMD python ./src/cloud_agent.py
FROM python:3.4-alpine

WORKDIR /server_warehouse
VOLUME ["/server_warehouse/server_warehouse"]
COPY requirements.txt /server_warehouse

RUN apk update && \
 apk add postgresql-libs && \
 apk add --virtual .build-deps gcc musl-dev postgresql-dev && \
 python3 -m pip install -r requirements.txt --no-cache-dir && \
 apk --purge del .build-deps

COPY runserver.py /server_warehouse
COPY test.py /server_warehouse

CMD python test.py;\
    python runserver.py

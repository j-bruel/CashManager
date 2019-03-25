FROM python:3.4-alpine

WORKDIR /server_bank
VOLUME ["/server_bank/server_bank"]
COPY requirements.txt /server_bank

RUN apk update && \
 apk add postgresql-libs && \
 apk add --virtual .build-deps gcc musl-dev postgresql-dev && \
 python3 -m pip install -r requirements.txt --no-cache-dir && \
 apk --purge del .build-deps

COPY runserver.py /server_bank
COPY test.py /server_bank

CMD python test.py;\
    python runserver.py

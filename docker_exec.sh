#! /bin/bash
IMAGE=boot1:unc
if [[ -z $(docker images --format json $IMAGE) ]] 
then
    pushd $(git rev-parse --show-toplevel) > /dev/null
    docker volume create bustub-volume && docker build . -t $IMAGE -f Dockerfile
    popd > /dev/null
fi

if [[ -z $(docker ps | grep $IMAGE) ]]
then
    CONTAINER_ID=$(docker run -d -v bustub-volume:/workspace/421-bootcamp $IMAGE)
else
    CONTAINER_ID=$(docker ps -f ancestor=$IMAGE --format="{{.ID}}")
fi
docker exec -it -w /workspace/421-bootcamp "${CONTAINER_ID}" /bin/bash

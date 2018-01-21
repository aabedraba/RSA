pipeline {
    agent {
      docker { image 'aabedraba/rsa' }
    }
    stages {
        stage('Build') {
            steps {
                echo 'Building..'
                cd build
                echo 'In build folder. CMake in progress..'
                cmake ..
                make
            }
        }
    }
}

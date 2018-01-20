pipeline {
    agent { docker 'aabedraba/aabedraba:latest' }
    stages {
        stage('build') {
            steps {
                sh 'cd build'
                sh 'cmake ..'
                sh 'make'
                sh './RSA'
            }
        }
    }
}
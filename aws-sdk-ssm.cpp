﻿// aws-sdk-ssm.cpp : Defines the entry point for the console application.
//

#include <aws/core/Aws.h>
#include <aws/ssm/SSMClient.h>

#include <aws/ssm/model/PutParameterRequest.h>
#include <aws/ssm/model/PutParameterResult.h>

#include <aws/ssm/model/GetParametersRequest.h>

#include <aws/core/utils/Outcome.h>

#include <aws/core/utils/logging/DefaultLogSystem.h>
#include <aws/core/utils/logging/AWSLogging.h>

#include <iostream>


namespace {

auto& ssm()
{
    static Aws::SSM::SSMClient client;
    return client;
}

} // namespace

int main()
{
    try 
    {
        Aws::Utils::Logging::InitializeAWSLogging(
            Aws::MakeShared<Aws::Utils::Logging::DefaultLogSystem>(
                "RunUnitTests", Aws::Utils::Logging::LogLevel::Trace, "aws_sdk_"));
        Aws::SDKOptions options;
        Aws::InitAPI(options);

        auto getParametersOutcome = ssm().GetParameters(
            Aws::SSM::Model::GetParametersRequest().WithNames({ "APPLICATION_SECRET_API_KEY" }).WithWithDecryption(true));

        if (getParametersOutcome.IsSuccess())
        {
            std::cout << getParametersOutcome.GetResult().GetParameters()[0].GetValue() << '\n';
        }

        Aws::ShutdownAPI(options);
        Aws::Utils::Logging::ShutdownAWSLogging();
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << '\n';
        return 1;
    }

    return 0;
}

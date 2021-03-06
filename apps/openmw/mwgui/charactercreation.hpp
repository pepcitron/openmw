#ifndef CHARACTER_CREATION_HPP
#define CHARACTER_CREATION_HPP

#include "window_manager.hpp"

#include "../mwmechanics/mechanicsmanager.hpp"
#include "../mwmechanics/stat.hpp"
#include "../mwworld/world.hpp"
#include <components/esm_store/store.hpp>

namespace MWGui
{
    class WindowManager;
    class WindowBase;

    class TextInputDialog;
    class InfoBoxDialog;
    class RaceDialog;
    class DialogueWindow;
    class ClassChoiceDialog;
    class GenerateClassResultDialog;
    class PickClassDialog;
    class CreateClassDialog;
    class BirthDialog;
    class ReviewDialog;
    class MessageBoxManager;

    class CharacterCreation
    {
    public:
    typedef std::vector<int> SkillList;

    CharacterCreation(WindowManager* _wm);
    ~CharacterCreation();

    //Show a dialog
    void spawnDialog(const char id);

    void setPlayerHealth (const MWMechanics::DynamicStat<int>& value);

    void setPlayerMagicka (const MWMechanics::DynamicStat<int>& value);

    void setPlayerFatigue (const MWMechanics::DynamicStat<int>& value);

    private:
    //Dialogs
    TextInputDialog* mNameDialog;
    RaceDialog* mRaceDialog;
    DialogueWindow* mDialogueWindow;
    ClassChoiceDialog* mClassChoiceDialog;
    InfoBoxDialog* mGenerateClassQuestionDialog;
    GenerateClassResultDialog* mGenerateClassResultDialog;
    PickClassDialog* mPickClassDialog;
    CreateClassDialog* mCreateClassDialog;
    BirthDialog* mBirthSignDialog;
    ReviewDialog* mReviewDialog;

    WindowManager* mWM;

    //Player data
    std::string mPlayerName;
    std::string mPlayerRaceId;
    std::string mPlayerBirthSignId;
    ESM::Class mPlayerClass;
    std::map<ESM::Attribute::AttributeID, MWMechanics::Stat<int> > mPlayerAttributes;
    SkillList mPlayerMajorSkills, mPlayerMinorSkills;
    std::map<ESM::Skill::SkillEnum, MWMechanics::Stat<float> > mPlayerSkillValues;
    MWMechanics::DynamicStat<int> mPlayerHealth;
    MWMechanics::DynamicStat<int> mPlayerMagicka;
    MWMechanics::DynamicStat<int> mPlayerFatigue;

    //Class generation vars
    unsigned mGenerateClassStep;                 // Keeps track of current step in Generate Class dialog
    unsigned mGenerateClassSpecializations[3];   // A counter for each specialization which is increased when an answer is chosen
    std::string mGenerateClass;                  // In order: Stealth, Combat, Magic

    ////Dialog events
    //Name dialog
    void onNameDialogDone(WindowBase* parWindow);

    //Race dialog
    void onRaceDialogDone(WindowBase* parWindow);
    void onRaceDialogBack();

    //Class dialogs
    void onClassChoice(int _index);
    void onPickClassDialogDone(WindowBase* parWindow);
    void onPickClassDialogBack();
    void onCreateClassDialogDone(WindowBase* parWindow);
    void onCreateClassDialogBack();
    void showClassQuestionDialog();
    void onClassQuestionChosen(int _index);
    void onGenerateClassBack();
    void onGenerateClassDone(WindowBase* parWindow);

    //Birthsign dialog
    void onBirthSignDialogDone(WindowBase* parWindow);
    void onBirthSignDialogBack();

    //Review dialog
    void onReviewDialogDone(WindowBase* parWindow);
    void onReviewDialogBack();
    void onReviewActivateDialog(int parDialog);

    enum CSE    //Creation Stage Enum
    {
        CSE_NotStarted,
        CSE_NameChosen,
        CSE_RaceChosen,
        CSE_ClassChosen,
        CSE_BirthSignChosen,
        CSE_ReviewNext
    };

    CSE mCreationStage; // Which state the character creating is in, controls back/next/ok buttons
    };
}

#endif
